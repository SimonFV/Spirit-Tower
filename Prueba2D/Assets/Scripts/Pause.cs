using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class Pause : MonoBehaviour
{
    public static bool gameIsPaused = false;

    public GameObject PauseMenu;
    public Text status;

    // Update is called once per frame
    void Update()
    {
        if (gameIsPaused)
        {
            pause();
        }
    }

    public void reconnect()
    {
        PauseMenu.SetActive(false);
        Time.timeScale = 1f;
        gameIsPaused = false;
        Win.scene = 2;
        SceneManager.LoadScene(0);
    }

    public void pause()
    {
        PauseMenu.SetActive(true);
        Time.timeScale = 0f;
    }
}
